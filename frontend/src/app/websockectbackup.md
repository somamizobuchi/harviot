import { Injectable } from '@angular/core';
import { over } from '@stomp/stompjs';
import * as SockJS from 'sockjs-client';

@Injectable({
  providedIn: 'root'
})
export class WebsocketService implements OnDestroy{
  private client: Client;
  private state: BehaviorSubject<SocketClientState>;
  enum SocketClientState {
    ATTEMPTING, CONNECTED
  }

  constructor() {
    this.client = over(new SockJS(environment.api));
    this.state = new BehaviorSubject<SocketClientState>(SocketClientState.ATTEMPTING);
    this.client.connect({}, () => {
      this.state.next(SocketClientState.CONNECTED);
    });
  }

  private connect(): Observable<Client> {
    return new Observable<Client>(observer => {
      this.state.pipe(filter(state => state === SocketClientState.CONNECTED)).subscribe(() => {
        observer.next(this.client);
      });
    });
  }

  ngOnDestroy() {
    this.connect().pipe(first()).subscribe(client => client.disconnect(null));
  }

  static jsonHandler(message: Message): any {
    return JSON.parse(message.body);
  }
  
  static textHandler(message: Message): string {
    return message.body;
  }

  onMessage(topic: string, handler = SocketClientService.jsonHandler): Observable<any> {
    return this.connect().pipe(first(), switchMap(client => {
      return new Observable<any>(observer => {
        const subscription: StompSubscription = client.subscribe(topic, message => {
          observer.next(handler(message));
        });
        return () => client.unsubscribe(subscription .id);
      });
    }));
  }

  onPlainMessage(topic: string): Observable<string> {
    return this.onMessage(topic, SocketClientService.textHandler);
  }

  send(topic: string, payload: any): void {
    this.connect()
      .pipe(first())
      .subscribe(client => client.send(topic, {}, JSON.stringify(payload)));
  }
}


/***
…and subscribing to the messages observable in your Angular component to receive the most recent values.

liveData$ = this.service.messages$.pipe(
  map(rows => rows.data),
  catchError(error => { throw error }),
  tap({
    error: error => console.log('[Live component] Error:', error),
    complete: () => console.log('[Live component] Connection Closed')
  }
  )
);


****/