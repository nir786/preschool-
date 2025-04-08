minComp - Minimalist Brain-Melting Compiler/doesnt work(gave up at the end)/over complicated calculator 
This project is a hand-written C compiler that tokenizes simple math expressions,
builds an AST, and then prints the corresponding x86_64 assembly directly to your terminal.
No file input. 
No file output.
No safety checks.
No sanity.
I belive I forgot to garbege collect. 


Features
Tokenizes integers and basic math ops: +, -, *, /
Builds 2 binary AST(I think) one for * and / and one for + - the idea behind it was to do order of operations without losing my sanity
with implicit operator precedence
Walks the tree and screams NASM-style assembly using printf pretty sure the assembly is wrong it's been years since I touched assembly 
Evaluates expressions using stack-based simulated logic

Why?
I wanted to understand how compilers work.
Then I wanted to see how far I could push it.


Status
I did the multiplication tree assembly generation. It might be cursed.
I'm not running it. I'm not debugging it. I'm not touching it anymore.

If you're reading this: Why ?
overall I think it was a great learning experiance defo shouldn't have attempted this as a first project 

— Nir
