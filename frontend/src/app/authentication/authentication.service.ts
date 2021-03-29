import { Injectable } from '@angular/core';
import { SignInData } from 'src/app/model/signInData';
import {Router} from '@angular/router';
import { HttpClient } from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class AuthenticationService {
  private isAuthenticated = false;
  private isUser: string = "";
  errorMessage:any;
  constructor(private router: Router, private http: HttpClient) { }

 
  /**
   * LOGIN
  */
  // If credentials are valid then set authentication to tue and navigate to userview
  authenticate(signInData: SignInData){
    if(this.checkCredentials(signInData)){
      this.isAuthenticated = true;
      this.router.navigate(['userView'])
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
    const body = { email: signInData.getEmail, password: signInData.getPassword};
    this.http.post<any>('http://api.harviot.com/auth?entity=user',body).subscribe({
        next: data => {
            this.isUser = data._ent;
            console.log(data);
        },
        error: error => {
            this.errorMessage = error.message;
            console.error('There was an error!', error);
        }
    })
    return this.isUser === "user";
  }
  //return isAuthenticated
  public returnAuth():boolean{
    return this.isAuthenticated;
  }


}