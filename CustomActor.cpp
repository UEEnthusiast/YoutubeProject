// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomActor.h"

// Sets default values
ACustomActor::ACustomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ACustomActor::BeginPlay()
{
	Adding();
	Iterating();
	Sorting();
	Querying();
	Removing();
	Operators();
	Heap();
}

void ACustomActor::Adding()
{
	TArray<int32> intArray;

	// Init
	intArray.Init(10, 2);

	// Add
	intArray.Add(20);

	// Emplace
	intArray.Emplace(30);

	// AddUnique
	intArray.AddUnique(20);

	// Push
	intArray.Push(20);

	// Push but passing const
	const int32 val = 32;
	intArray.Push(val);

	// [] operator
	intArray[0] = 1;

	// Insert
	intArray.Insert(1, 2);

	// Insert_GetRef
	int& a = intArray.Insert_GetRef(1, 2);
	a = 999;

	// SetNum
	intArray.SetNum(20);

	// Append - initializer list
	intArray.Append({ 1,2,3,5 });

	// Append - passing TArray
	TArray<int32> intArraySecond = { 1, 2, 3 };
	intArray.Append(intArraySecond);

	// AddUninitialized
	int32 arr[] = { 1, 2, 3, 4 };
	TArray<int32> intArr;
	intArr.AddUninitialized(4);
	FMemory::Memcpy(intArr.GetData(), arr, 4 * sizeof(int32));

}

void ACustomActor::Iterating()
{
	TArray<FString> myStringArray = { "value", "value", "value" };

	// Foreach with copy
	for (FString value : myStringArray) //  (auto value : MyStringArray)
	{
		const FString string = value + " changed";
	}

	// Foreach with a ref
	for (FString& value : myStringArray)
	{
		value = "replaced";
	}

	//index-Based iteration
	for (int32 index = 0; index != myStringArray.Num(); ++index)
	{
		const FString str = myStringArray[index];
	}

	// CreateIterator
	for (auto it = myStringArray.CreateIterator(); it; ++it)
	{
		*it += " again";
	}
	// CreateConstIterator
	for (auto it = myStringArray.CreateConstIterator(); it; ++it)
	{
		const FString str = *it; // see It as a
		FString b = *str; // or if you want to change b lately

		//*It += " impossible";
	}
}

void ACustomActor::Sorting()
{
	// Sort
	TArray<FString> myStringArray = { "aa", "ccc","ddd", "eee", "b" };
	myStringArray.Sort();

	// Sort with Predicate
	myStringArray.Sort([](const FString& a, const FString& b) {
		return a.Len() < b.Len();
	});

	// Sort with Static Predicate
	myStringArray.Sort(ACustomActor::CompareLength);

	int localInt = 10;
	bool refBool = true;

	// Sort when passing value & ref
	myStringArray.Sort([localInt, &refBool](const FString& a, const FString& b) {
		if (localInt == 0)
		{
			return true;
		}
		return (refBool)
			? a.Len() < b.Len()
			: a.Len() > b.Len();
	});

	TArray<FString> myStringArray2 = { "aa", "ccc","ddd", "eee", "b" };

	// StableSort
	myStringArray2.StableSort([](const FString& a, const FString& b) {
			return a.Len() < b.Len();
	});

	// HeapSort
	myStringArray2.HeapSort([](const FString& a, const FString& b) {
		return a.Len() < b.Len();
	});
}

void ACustomActor::Querying()
{
	TArray<FString> myStringArr = { "aa", "ccc","ddd", "eee", "b" };

	// Num
	int32 count = myStringArr.Num();

	//2) GetData
	FString* strPtr = myStringArr.GetData();
	FString a = strPtr[0];
	FString b = strPtr[1];
	/*FString c = StrPtr[6]; undefined behavior */

	// const GetData
	const TArray<FString> myStringArrConst = { "aa", "ccc","ddd", "eee", "b" };
	const FString * strPtrConst = myStringArrConst.GetData();

	// GetTypeSize
	uint32 ElementSize = myStringArr.GetTypeSize();

	// []
	FString Elem1 = myStringArr[1];
	/*FString Elem2 = myStringArr[6]; undefined behavior */

	// IsValidindex
	bool invalid = myStringArr.IsValidIndex(-1);
	bool valid = myStringArr.IsValidIndex(1);
	bool invalid2 = myStringArr.IsValidIndex(5);

	// RangeCheck
	myStringArr.RangeCheck(1);
	myStringArr.RangeCheck(5);

	// Last & Top
	FString elemEnd = myStringArr.Last();
	FString elemEndSame = myStringArr.Last(0); // same as MyStringArr.Last()
	FString elemBeforeEnd = myStringArr.Last(1);

	FString elemEndTop = myStringArr.Top(); // same as MyStringArr.Last()

	// Contains
	bool bDDD = myStringArr.Contains(TEXT("ddd"));
	bool bH = myStringArr.Contains(TEXT("h"));

	// ContainsByPredicate
	bool bLen1 = myStringArr.ContainsByPredicate([](const FString& Str) {
		return Str.Len() == 1;
	});

	bool bLen7 = myStringArr.ContainsByPredicate([](const FString& Str) {
		return Str.Len() == 7;
	});

	// Find returns bool
	int32 indexFound;
	bool found = myStringArr.Find(TEXT("aa"), indexFound);

	// Find returns index
	int32 indexFoundDirectly = myStringArr.Find(TEXT("abc")); // index_NONE == -1
	int32 indexFoundDirectly2 = myStringArr.Find(TEXT("ccc")); // 1

	// FindLast
	int32 indexFound2;
	bool found2 = myStringArr.FindLast(TEXT("aa"), indexFound2);

	// FindByKey
	FString* elemStrPtr0 = myStringArr.FindByKey(TEXT("ccc"));

	// indexOfByKey
	int32 index = myStringArr.IndexOfByKey(TEXT("ccc"));

	// indexOfByPredicate
	int32 index2 = myStringArr.IndexOfByPredicate([](const FString& str) {
		return  str.Len() == 3;
	});

	// FindByPredicate
	FString* elemStrPtr = myStringArr.FindByPredicate([](const FString& str) {
		return str.Len() == 3;
	});

	// FilterByPredicate
	TArray<FString> filter = myStringArr.FilterByPredicate([](const FString& str) {
		return !str.IsEmpty() && str[0] == 'c';
	});
}

void ACustomActor::Removing()
{
	TArray<int32> intArray = { 10, 20, 30, 5, 10, 15, 20, 25, 30 };

	// Remove
	intArray.Remove(10);

	// RemoveSingle
	intArray.RemoveSingle(20);

	// RemoveAt
	intArray.RemoveAt(0);
	intArray.RemoveAt(0, 2, true);

	// RemoveAll
	intArray.RemoveAll([](int32 Val) {
		return Val % 2 == 0;
	});


	TArray<int32> valArr2 = { 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 5, 10, 11 };

	// RemoveAtSwap, RemoveAtSwap, RemoveAllSwap and RemoveSingleSwap
	valArr2.RemoveSwap(2);
	valArr2.RemoveAtSwap(1);
	valArr2.RemoveAllSwap([](int32 Val) {
		return Val % 3 == 0;
	});
	valArr2.RemoveSingleSwap(4);

	// Empty
	valArr2.Empty();

	TArray<int32> valArr3 = { 0, 1, 2, 3, 4, 0, 1, 2, 3, 4 };

	// SetNum
	valArr3.SetNum(2);
}

void ACustomActor::Operators()
{
	// "=" operator
	TArray<int32> numbers = { 1, 2, 3, 4, 5 }; // initializer list
	TArray<int32> numbersCopied = numbers; // Copy a TArray to Another
	numbersCopied[0] = 0;


	// "=" operator with MoveTemp
	TArray<int32> beforeMoveTemp = { 1, 2, 3, 4, 5 };
	TArray<int32> afterMoveTemp;
	afterMoveTemp = MoveTemp(beforeMoveTemp);


	// "+=" operator (Append alternative)
	numbersCopied += {10, 10, 10};

	// "==" operator
	TArray<FString> flavorArr1 = { "Chocolate", "Vanilla" };
	TArray<FString> flavorArr2 = { "Chocolate", "Vanilla" };

	TArray<FString> flavorArr3 = { "Chocolate", "Mint" };

	bool bComparison1 = (flavorArr1 == flavorArr2);
	bool bComparison2 = (flavorArr1 == flavorArr3);

	// "==" operator with Custom Class
	TArray<ACustomActor> customClassArray;
	TArray<ACustomActor> customClassArray2;

	bool bComparisonCustom = (customClassArray == customClassArray2); // will go in operator==(const ACustomActor& other) 
}

bool MaxHeapPredicate(int a, int b) {
	return a >= b;
}

void ACustomActor::Heap()
{
	// Heapify
	TArray<int32> heapArr = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	heapArr.Heapify();

	// HeapPush
	heapArr.HeapPush(4);

	// HeapPop & HeapPopDiscard
	int32 topNode = 0;
	heapArr.HeapPop(topNode); // heapArr.HeapPopDiscard(topNode);

	//HeapTop
	int32 top = heapArr.HeapTop();

	// HeapRemoveAt
	heapArr.HeapRemoveAt(1);

	// VerifyHeap
	heapArr.VerifyHeap([](const int& a, const int& b) { return a >= b; });

	// Algo::IsHeap()
	const bool isHeap = Algo::IsHeap(heapArr);
	TArray<int32> notHeapArr = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	const bool isHeap2 = Algo::IsHeap(notHeapArr);

	// Heapify methods with custom predicates
	auto isMore = [](const int32& a, const int32& b) {
		return a > b;
	};

	// check inside Heapify -> TLess<ElementType>() used by default, also named "min heap"
	heapArr.Heapify(isMore); 
	heapArr.HeapPopDiscard(isMore);


	// HeapSort
	heapArr.HeapSort(); //A < B
	heapArr.HeapSort(isMore);//A > B
}
