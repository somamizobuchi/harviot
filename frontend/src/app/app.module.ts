import { CUSTOM_ELEMENTS_SCHEMA, NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { HomeComponent } from './home/home.component';
import { RegisterComponent } from './register/register.component';
import { LoginComponent } from './login/login.component';
import { FormsModule } from '@angular/forms';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { DefaultModule } from './layouts/default/default.module';
import { SharedModule } from './shared/shared.module';
import { SocketIoModule, SocketIoConfig } from 'ngx-socket-io';
import { AuthGuard } from './guards/auth.guard';
import { AuthenticationService } from './authentication/authentication.service';
import { HttpClientModule } from '@angular/common/http';
import { SocketService } from './services/socket.service';
import { PlantUserService } from './services/plant-user.service';
import { DashboardComponent } from './modules/dashboard/dashboard.component';
import { PchartComponent } from './modules/pchart/pchart.component';


const config: SocketIoConfig = { url: 'http://api.harviot.com/', options: {} };

@NgModule({
  declarations: [
    AppComponent,
    HomeComponent,
    RegisterComponent,
    LoginComponent,
    PchartComponent

  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    FormsModule,
    BrowserAnimationsModule,
    DefaultModule,
    SharedModule,
    SocketIoModule.forRoot(config),
    HttpClientModule
  ],
  schemas: [ CUSTOM_ELEMENTS_SCHEMA],
  providers: [AuthGuard,AuthenticationService,SocketService,PlantUserService],
  bootstrap: [AppComponent]
})
export class AppModule { }
