import {User} from './user';
import {Action} from './action';

export interface Message {
    from?: User;
    action?: Action;
    id: string;
    body: string;
}