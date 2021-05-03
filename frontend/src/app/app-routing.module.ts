import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { HomeComponent } from './home/home.component';
import { LoginComponent } from './login/login.component';
import { RegisterComponent } from './register/register.component';
import { DefaultComponent} from './layouts/default/default.component';
import { PhysicalComponent} from './modules/physical/physical.component';
import { DashboardComponent} from './modules/dashboard/dashboard.component';
import { AuthGuard } from './guards/auth.guard';
 
const routes: Routes = [
  {path: '', component: HomeComponent},
  {path: 'login', component: LoginComponent},
  {path: 'register', component: RegisterComponent},
  {path: 'userView', component: DefaultComponent, children: [{path: 'userView',
    component: DashboardComponent
  }], canActivate: [AuthGuard]},
  {path: 'physical', component: PhysicalComponent},
  {path: '**', redirectTo: ''}
];
 
@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
 
 

