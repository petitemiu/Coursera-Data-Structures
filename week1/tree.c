#include <stdio.h>
#include <stdlib.h>

struct tree{
	int parent;
	size_t height;
};

size_t compute(struct tree* begin, size_t elem, size_t length){
	if(begin[elem].height > 0){
		return begin[elem].height;
	}
	if(begin[elem].parent == -1){
		begin[elem].height = 1;
		return 1;
	}
	else{
		begin[elem].height = compute(begin, begin[elem].parent, length) + 1;
		return begin[elem].height;
	}
}

int main(void){
	size_t count = 0, i = 0, max = 0; 
	scanf("%lu", &count);

	struct tree* arr = calloc(count, sizeof(struct tree));
	
	for(i; i < count; ++i){
		scanf("%d", &arr[i].parent);
		arr[i].height = 0;
	}
	
	for(i = 0; i < count; ++i){
		size_t tmp = compute(arr, i, count);
		if(tmp > max){
			max = tmp;
		}
	}
	printf("%lu\n", max);
	return 0;
} 
