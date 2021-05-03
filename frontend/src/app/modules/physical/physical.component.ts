import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';

interface sensVal {
  temperature: string;
  humidity: string;
  ambient_light: string;
}

interface resPonse{
  sensorValues:sensVal;
  date:string
}

@Component({
  selector: 'app-physical',
  templateUrl: './physical.component.html',
  styleUrls: ['./physical.component.css']
})

export class PhysicalComponent implements OnInit {
  private SignInPostURL:string = "http://api.harviot.com/auth?entity=user";
  private PlantDataURL:string = "http://api.harviot.com/plants/logs/?plant_id=6021f39b3e64fd8d1fc5c2aa";

  plantData: any = [];
  humidity:string[] = [];
  temperature:number[] = [];
  ambientlight:number[] = [];
  constructor(private http: HttpClient) { }

  
  ngOnInit(): void {
    // this.http.get(this.PlantDataURL).toPromise().then(
    //   data => {
    //     console.log(data);
    //   }
    // )

    this.http.get("assets/response.json").subscribe(data =>{
      console.log(data);
      Object.entries(data).forEach(logs =>{
        logs.map(log => log.sensorValues.humidity)
        console.log(logs)
      })
      // data.response.forEach(element => {  this.humidity = 
      //   this.humidity.push(element.Id);
    });
      // for(let obj in this. plantData){
      //   console.log(obj['sensorValues']);
      // }
    
  }

  
}
