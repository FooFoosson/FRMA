# FRMA - Function Runtime Measurment Api
---
FRMA is a simple C++ library for profiling function runtime with a focus on usage simplicity.
## Usage
Let's say you have a function foo and a method bar: 
```
int foo(int a, int b);

class Test{
	void bar();
}
```
To measure their runtime simply call the profile method which takes the following arguments:

1. procedure name to be displayed in the html output
2. address of the procedure
3. arguments to be passed to the procedure

Like so:
```
frma::Perf& perf = frma::Perf::getInstance();
unsigned long long fooMilisecRuntime = perf.profile("foo", foo, 1, 2);

Test t;
unsigned long long barMilisecRuntime = perf.profile("bar", &Test::bar, &t);
*//where t is the this pointer*
```
You can also view the generated html page by going into reports/ and opening perf_report.html in your favourite browser.
![alt text](https://github.com/FooFoosson/FRMA/wiki/Example)
