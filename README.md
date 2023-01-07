# jcs
jcs is a translator for jcs-script to javascript. For now it's still and developement and isn't usable for real projects.
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
public static class Main
{
    private String str;

    public static void Main()
    {
        this.str = "Hello World";
        console.log(this.getStr());

        // create a new Program
        new Program();
    }

    private static void getStr()
    {
        return this.str;
    }
}

public class Program
{
    public Program()
    {
        console.log("Starting my program...");
    }
}
```
This code will be translated as :
```javascript
class Main 
{ 
    str; 
    static Main() 
    { 
        this.str = "Hello World"; 
        console.log(this.getStr()); 
        new Program(); 
    } 
    static getStr() 
    { 
        return this.str; 
    } 
} 
class Program 
{ 
    constructor()
    { 
        console.log("Starting my program..."); 
    } 
} 
Main.Main();
```
