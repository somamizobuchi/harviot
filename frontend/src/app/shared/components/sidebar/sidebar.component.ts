import { Component, OnDestroy, OnInit } from '@angular/core';
import { AuthenticationService } from './../../../authentication/authentication.service';
import { ShareuserdataService } from '../../../shareuserdata.service';
import { Subscription} from 'rxjs';

@Component({
  selector: 'app-sidebar',
  templateUrl: './sidebar.component.html',
  styleUrls: ['./sidebar.component.css']
})
export class SidebarComponent implements OnInit, OnDestroy {
  message:string = "";
  subscription = new Subscription;

  constructor(private authenticationService: AuthenticationService, private sds:ShareuserdataService) { }

  ngOnInit(): void {
    this.subscription = this.sds.currentMessage.subscribe(message => this.message = message)
  }
  
  ngOnDestroy(){
    this.subscription.unsubscribe();
  }

  navigatePhysical(){
    this.sds.changeMessage("phys");
  }

  navigateDashboard(){
    this.sds.changeMessage("dash");
  }

  printFirstName(){
    return this.authenticationService.returnfirstName();
  }

  printEmail(){
    return this.authenticationService.returnEmail();
  }
}
 