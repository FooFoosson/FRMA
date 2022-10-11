# FRMA - Function Runtime Measurment Api
FRMA is a simple C++ library for profiling function runtime with a focus on usage simplicity.
## Usage
Let's say you have a function foo, a non static method bar and a static method buzz: 
```
int foo(int a, int b);

class Test{
	void bar();
	static void buzz();
};
```
To measure their runtime simply call the profile method which takes the following arguments:

1. Procedure name to be displayed in the html output.
2. Address of the procedure(rules are same as with std::thread construction).
3. Arguments to be passed to the procedure.

Like so:
```
frma::Perf& perf = frma::Perf::getInstance();

unsigned long long fooMilisecRuntime = perf.profile("foo", foo, 1, 2);
/* same calling convention if foo was a functor */

Test t;
unsigned long long barMilisecRuntime = perf.profile("bar", &Test::bar, &t);
/* where t is the this pointer */

unsigned long long buzzMilisecRuntime = perf.profile("buzz", &Test::buzz);
```
You can also view the generated html page by going into reports/ and opening perf_report.html in your favourite browser.
![alt text](https://user-images.githubusercontent.com/112069209/195075493-ce0d9110-3d6d-45fc-a3a6-23102287abfa.png)
