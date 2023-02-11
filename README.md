# Sakora
![https://badgen.net/badge/icon/windows?icon=windows&label](https://badgen.net/badge/icon/windows?icon=windows&label)
![https://badgen.net/badge/icon/github?icon=github&label](https://badgen.net/badge/icon/github?icon=github&label)

## Introduction
Sakora is an interpretive language based on Yolang and Eytion;  
In Sakora, you will see the similarities with Yolang and Eytion.  
However, he is more excellent and efficient than Yolang and Eytion

## License
This project uses MIT license  
You can view the license of this project through the following this [link](LICENSE)

## How to USE?
Sakora is divided into two types: Build and Release  

**Release** version You need to select a version by yourself through the "Release" on the right side of the project, where you can obtain the entire software package (except for the executable file)  

**Build** is the result automatically compiled through Action (only executable files).  
The result may be unstable or even have serious vulnerabilities.  
Please use it with caution; 
Of course, in most cases you can use the Build version to try something new.  
After you obtain the files of Build version, you need to replace the executable files in the original software package of Sakora (named "sakora", and the suffix depends on the system)

## Demo (future)
hello world
```rust
let a: string = "hello, world!";
println(a);
```
variable
```rust
let v1: int = 435; // default: int32
v1 = 6;

let v2 = "hello, world!"; // Typeable derivation

println(v1);
println(v2);
```
function
```rust
fn foo(a: int, b: int)->int {
    return a+b;
}

println(foo(1, 2));

// Also, you can:

let add1: fn(int, int)->int = fn(a, b) {
    return a + b;
}

// or:

let add2: fn(int, int)->int = fn(a: int, b: int)->int {
    return a + b;
}
```

## Contributors
### [**PowerAngelXD**](https://github.com/PowerAngelXD)  
**Initiator of the project**  
### [**FZZKill**](https://github.com/FZZkill)  
**The most active people who help improve the project**
### [**This-is-XiaoDeng**](https://github.com/This-is-XiaoDeng) 
**Help the Release version of this project compile the Linux version**