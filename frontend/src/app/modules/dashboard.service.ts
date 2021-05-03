import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class DashboardService {

  constructor() { }
  
  bigChart() {
    return [{
      name: 'Plant-1',
      data: [502, 635, 809, 947, 1402, 3634, 5268,6776]
    }, {
      name: 'Plant-2',
      data: [106, 107, 111, 133, 221, 767, 1766,2332]
    }, {
      name: 'Plant-3',
      data: [163, 203, 276, 408, 547, 729, 628,1001]
    }, {
      name: 'Plant-4',
      data: [18, 31, 54, 156, 339, 818, 1201,2112]
    }, {
      name: 'Plant-5',
      data: [2, 2, 2, 6, 13, 30, 46,55]
    }];
  }

  cards() {
    return [71, 78, 39, 66];
  }

  pieChart() {
    return [{
      name: 'Chrome',
      y: 61.41,
      sliced: true,
      selected: true
    }, {
      name: 'Internet Explorer',
      y: 11.84
    }, {
      name: 'Firefox',
      y: 10.85
    }, {
      name: 'Edge',
      y: 4.67
    }, {
      name: 'Safari',
      y: 4.18
    }, {
      name: 'Sogou Explorer',
      y: 1.64
    }, {
      name: 'Opera',
      y: 1.6
    }, {
      name: 'QQ',
      y: 1.2
    }, {
      name: 'Other',
      y: 2.61
    }];
  }
}