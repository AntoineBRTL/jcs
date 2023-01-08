# jcs
jcs is a transpiler for jcs-script to javascript. For now it's still and developement and isn't usable for real projects.
You can still try it and help me finding bugs to make a stable version.

## Installation ##
* You simply have to download the bin dir which contains jcs compiler itself. 
* You can also download the source code and recompile it using [gcc](https://gcc.gnu.org/) or an other c++ compiler. 

Don't forget to add the bin directory to the Path variable of your machine.

## How to use ##
To translate your code in javascript run the following command:

* `jcs myFile.jcs myFile.js`

Then you have your full code translated in js

## Exemple ##
jcs-script uses the same syntax as C-Sharp : 
```c#
public class Program
{
    private String str;

    public Program()
    {
        this.str = "Hello World";
    }

    public void getStr()
    {
        return this.str;
    }
}

public static class Main
{
    private Program program;

    public static void Main()
    {
        this.program = new Program();
        console.log(this.program.getStr());   
    }
}
```
This code will be translated as :
```javascript
class Program 
{ 
    str; 
    constructor()
    { 
        this.str = "Hello World"; 
    } 
    getStr() 
    { 
        return this.str; 
    } 
} 
class Main 
{ 
    program; 
    static Main() 
    { 
        this.program = new Program(); 
        console.log(this.program.getStr());   
    } 
} 
Main.Main();
```
