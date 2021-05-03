import {User} from './user';


export interface Message {
    from?: User;
    id: string;
    body: string;
}
