import { Component, OnInit } from '@angular/core';
import { SignInData } from 'src/app/model/signInData';
import { NgForm} from '@angular/forms';
import { Router } from '@angular/router';
import { HttpClient } from '@angular/common/http';
import { AuthenticationService } from '../authentication/authentication.service';

@Component({
  selector: 'app-register',
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.css']
})
export class RegisterComponent implements OnInit {
  //declare alert message flags
  isFormInvalid = false;
  userAlreadyExists = false;
  errorMessage !:any;
  private SignUpPostURL:string = "http://api.harviot.com/users";
  constructor(private router: Router, private http: HttpClient, private authenticationService: AuthenticationService) { }

  ngOnInit(): void {
  }

  /**
   * REGISTER
   */
   signUp(registerForm: NgForm){
    const body = { firstname:registerForm.value.firstname, lastname:registerForm.value.lastname, email: registerForm.value.email, password: registerForm.value.password};
    this.http.post<any>(this.SignUpPostURL,body, {observe: 'response'}).subscribe({
        next: data => {
        },
        error: error => {
            this.errorMessage = error.message;
            console.error('There was an error!', error);
        }
    })
  }

  onSubmit(registerForm: NgForm){
    // If form is not valid let user know what fields to input
    if(!registerForm.valid){
      this.isFormInvalid = true;
      return;
    }
    else{
      //if user exists already set already exists flag and redirect to login
      const userData = new SignInData(registerForm.value.email, registerForm.value.password);
      if(this.authenticationService.checkCredentials(userData)){
        this.userAlreadyExists = true;
      }
      this.signUp(registerForm);
      this.router.navigate(['login']);      
    }
    
  }

}
