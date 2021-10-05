# CoffeeMaker Docs

### Detecting Memory Leaks

I use [Dr. Memory](https://drmemory.org/) in order to find memory leaks for this project.
I've found that using Dr. Memory as is can be quite slow. So I use the following options to limit the scope to just
finding memory leaks.

```bash
drmemory -leaks_only -- path/to/exe
```
