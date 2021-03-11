import { Injectable } from '@angular/core';
import {SignInData } from 'src/app/model/signInData';
import {Router} from '@angular/router'
@Injectable({
  providedIn: 'root'
})
export class AuthenticationService {
  private readonly mockedUser = new SignInData('akomearichard9@gmail.com','1234abc');
  isAuthenticated = false;
  constructor(private router: Router) { }
  authenticate(signInData: SignInData):boolean{
    
    if(this.checkCredentials(signInData)){
      this.isAuthenticated = true;
      this.router.navigate(['userView'])
      return true;
    }
    this.isAuthenticated = false;
    return false;
  }
  //used mock user here --  project should use socket connection to transmit data
  private checkCredentials(signInData: SignInData):boolean{
    return this.checkEmail(signInData.getEmail()) && this.checkPassword(signInData.getPassword());
  }
  private checkEmail(email: string):boolean{
    return email === this.mockedUser.getEmail();
  }
  private checkPassword(password: string):boolean{
    return password === this.mockedUser.getPassword();
  }
  logout(){
    this.isAuthenticated =false;
    this.router.navigate(['']);
  }
}
 
 

