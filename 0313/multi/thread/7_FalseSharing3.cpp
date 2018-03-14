#include <vector>
using namespace std;

// C++ 병렬 프로그래밍
//   1. Microsoft PPL(Parallel Pattern Library) - Windows
//   2. Intel TBB(Threading Building Blocks)
//      => Linux / Windows / Mac
//      => LGPL


// start_kernel
// copy_process

#include <tbb/tbb.h>
using namespace tbb;

struct data
{
	int value __attribute__((aligned(64)));
};

int main()
{
	// vector의 템플릿의 첫번째 인자: 요소의 타입
	//                   두전째 인자: 메모리 할당 정책 클래스
	// vector를 False Sharing의 문제에서 벗어나게 하고 싶다.
	// => tbb가 제공하는 cache_aligned_allocator<int>를 사용하면 된다.
	vector<int, cache_aligned_allocator<int> > v;

	// vector<data> v;
	// v[0], v[1]
}
