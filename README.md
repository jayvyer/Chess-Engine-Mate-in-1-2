## How to compile and run your code
1. Compile your project  
```bash
bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD
make all
```
2. Run your project  
```bash
./chess puzzles.txt solution.txt <mode>
```

3. Run test, make sure you have already set `LD_LIBRARY_PATH` using `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD`
```bash
./test <input>
```
For example: `./test "r3k2K/pppp4/8/8/8/8/p7/8 b q -"`
