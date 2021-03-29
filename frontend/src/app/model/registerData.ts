export class RegisterData{
    private firstName:string;
    private lastName:string;
    private email:string;
    private password:string;

    
    constructor(firstName:string, lastName:string, email:string, password:string){
        this.firstName = firstName;
        this.lastName = lastName;;
        this.email = email;
        this.password = password;
    }

    getFirstName():string{
        return this.firstName;
    }
    getLastName():string{
        return this.lastName;
    }
    getEmail():string{
        return this.email;
    }
    getPassword():string{
        return this.password;
    }
}