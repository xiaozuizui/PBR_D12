#include <apiquery2.h>
typedef UINT8 U8;
typedef UINT32 U32;

class Allocator
{

public:
	virtual void* alloc(U32 size) = 0;
	virtual void clear();

};

class StackAllocator : public Allocator
{
	typedef  U32 Marker;

public:
	explicit StackAllocator(U32 stackSize_bytes);
	void* alloc(U32 size) override;
	Marker getMarker();
	void FreeToMarker(Marker marker);
	void clear() override;
};


class AlignedAllocator:public Allocator
{
public:
	explicit AlignedAllocator(U32 alignedsize);
};