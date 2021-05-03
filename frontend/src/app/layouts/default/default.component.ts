import { Component, OnDestroy, OnInit } from '@angular/core';
import { AuthenticationService } from '../../authentication/authentication.service';
import { ShareuserdataService } from './../../shareuserdata.service';
import { Subscription } from 'rxjs';

@Component({
  selector: 'app-default',
  templateUrl: './default.component.html',
  styleUrls: ['./default.component.css']
})
export class DefaultComponent implements OnInit, OnDestroy {
  sideBarOpen = true;
  message: string = "";
  subscription = new Subscription;
  constructor(public authenticationService: AuthenticationService, private sds: ShareuserdataService) { }
  ngOnInit() { 
    this.subscription = this.sds.currentMessage.subscribe( message => this.message = message)
  }

  ngOnDestroy(){
    this.subscription.unsubscribe();
  }

  sideBarToggler() {
    this.sideBarOpen = !this.sideBarOpen;
  }

  navigateDashBoard(){

  }

  navigateInputQuery(){
    
  }
}
