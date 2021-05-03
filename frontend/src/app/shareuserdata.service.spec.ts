import { TestBed } from '@angular/core/testing';

import { ShareuserdataService } from './shareuserdata.service';

describe('ShareuserdataService', () => {
  let service: ShareuserdataService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(ShareuserdataService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
