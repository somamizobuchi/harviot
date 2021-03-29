import { Component, OnInit } from '@angular/core';
import { NgForm } from '@angular/forms';
import { SignInData } from '../model/signInData';
import { AuthenticationService } from '../authentication/authentication.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {
  isFormInvalid = false;
  areCredentialsInvalid = false;
  constructor(private authenticationService: AuthenticationService) { }
 
  ngOnInit(): void {
  }
 
  onSubmit(signInForm: NgForm){
    //if data doesn't match in database
    const signInData = new SignInData(signInForm.value.email, signInForm.value.password);
    if(!this.authenticationService.checkCredentials(signInData)){
      this.isFormInvalid = false;
      this.areCredentialsInvalid = true;
      return;
    }
    //if data form is invalid
    if(!signInForm.valid){
      this.isFormInvalid = true;
      this.areCredentialsInvalid = false;
      return;
    }
    //authenticate
    this.authenticationService.authenticate(signInData);
 
  }

}
 
 

