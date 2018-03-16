

#include <stdio.h>


class Foo
{
public:
	// void foo(Foo* this)
	void foo()
	{	
		if (this == 0)
			printf("this is null\n");

		printf("foo\n");
	}
};


int main()
{
	Foo* p = 0;

	p->foo(); // Foo::foo(p);
}

