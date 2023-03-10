<img src="./jcsicon.png" width="70"/>

# jcs lemon
jcs lemon is the first version of a transpiler for jcs-script (js with c-sharp & java syntax) to javascript. For now it's still in developement and isn't usable for real projects.
You can still try it and help me finding bugs to make a stable version.

## Installation ##
* You simply have to download the bin dir which contains jcs compiler itself. 
* You can also download the source code and recompile it using [gcc](https://gcc.gnu.org/) or an other c++ compiler. 

Don't forget to add the bin directory to the Path variable of your machine.

## How to use ##
To translate your code in javascript run the following command:

* ```bash
    jcs myFile.jcs myFile.js
    ```

Then you have your full code translated in js.
You can run the js file using :

* ```bash
    node myFile.js
    ```

And see it fully work

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
    private static Program program;

    // Entry
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
    static program; 
    static Main() 
    { 
        this.program = new Program(); 
        console.log(this.program.getStr());   
    } 
} 
Main.Main();
```
