import { TestBed } from '@angular/core/testing';

import { PlantUserService } from './plant-user.service';

describe('PlantUserService', () => {
  let service: PlantUserService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(PlantUserService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
