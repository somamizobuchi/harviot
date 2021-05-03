import { Injectable } from '@angular/core';
import { SignInData } from 'src/app/model/signInData';
import { Router } from '@angular/router';
import { HttpClient } from '@angular/common/http';
import { MessageReply } from './../model/mreply';
@Injectable({
  providedIn: 'root'
})
export class AuthenticationService {
  private isAuthenticated = false;
  private requestStatus:number = 0;
  errorMessage:any;
  private SignInPostURL:string = "http://api.harviot.com/auth?entity=user";
  private firstName:string = "";
  private lastName:string = "";
  private eMail:string = "";
  //const thisUser:User =;
  constructor(private router: Router, private http: HttpClient) { }
 
  /**
   * LOGIN
  */
  // If credentials are valid then set authentication to tue and navigate to userview
  authenticate(signInData: SignInData){
    if(this.checkCredentials(signInData)){
      this.isAuthenticated = true;
      this.router.navigate(['userView']);
      //put in login nmae and user email
      return;
    }
    this.isAuthenticated = false;
    return;
  }
  
  //set authentication to false and navigate to home

  logout(){
    this.isAuthenticated = false;
    this.router.navigate(['']);
  }

  // if entity is user then authenticate

  checkCredentials(signInData: SignInData):boolean{
      const body = { email: signInData.getEmail(), password: signInData.getPassword()};
      this.http.post<MessageReply>(this.SignInPostURL, body, {observe: 'response'}).subscribe({
          next: data => {
              this.requestStatus = data.status;
              //console.log(data);
              //console.log(this.returnAuth)
              this.firstName = data.body!.firstname;
              this.lastName = data.body!.lastname;
              this.eMail = data.body!.email;
          },
          error: error => {
              this.errorMessage = error.message;
              console.error('There was an error!', error);
          }
      })
    return (200 == this.requestStatus);
  }
  //return isAuthenticated
  public returnAuth():boolean{
    return this.isAuthenticated;
  }

  //return FN
  public returnlastName():string{
    return this.lastName;
  }

  //return LN
  public returnfirstName():string{
    return this.firstName;
  }

  //return E
  public returnEmail():string{
    return this.eMail;
  }


  // getConfigResponse(): Observable<HttpResponse<any>> {
  //   return this.http.post<any>(
  //     this.configUrl, { observe: 'response' });
  // }
  // httpOptions = {
  //   headers: new HttpHeaders({
  //     'Content-Type': 'application/json'
  //   })
  // }
}