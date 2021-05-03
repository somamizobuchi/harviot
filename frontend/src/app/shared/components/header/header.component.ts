import { Component, OnInit, Output, EventEmitter } from '@angular/core';
import { AuthenticationService } from './../../../authentication/authentication.service';

@Component({
  selector: 'app-header',
  templateUrl: './header.component.html',
  styleUrls: ['./header.component.css']
})
export class HeaderComponent implements OnInit {
  @Output() toggleSideBarForMe: EventEmitter<any> = new EventEmitter();

  constructor(private authenticationService: AuthenticationService) { }

  ngOnInit(): void {  }

  toggleSideBar() {
    this.toggleSideBarForMe.emit();
    setTimeout(() => {
      window.dispatchEvent(
        new Event('resize')
      );
    }, 300);
  }

  logout(){
   this.authenticationService.logout();
  }
}
