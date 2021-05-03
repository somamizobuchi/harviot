export class User {
    public email:string;
    public firstname: string;
    public lastname: string;
    
    constructor(email:string, firstname:string, lastname:string){
        this.email = email;
        this.firstname = firstname;
        this.lastname = lastname;
    }
    getEmail():string{
        return this.email;
    }
    getFirstName():string{
        return this.firstname;
    }
    getLastName():string{
        return this.lastname;
    }
}