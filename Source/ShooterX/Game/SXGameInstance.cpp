// SXGameInstance.cpp

#include "SXGameInstance.h"
#include "Example/SXFlyable.h"
#include "Example/SXEagle.h"
#include "Example/SXPigeon.h"

// Json활용 시 다음을 추가해준다.
// 이를위해 Build.cs에 "Json", "JsonUtilities" 두 가지 모듈을 반드시 추가해야 한다.
#include "JsonObjectConverter.h"
#include "UObject/SavePackage.h"

USXGameInstance::USXGameInstance()
{	
}

void USXGameInstance::Init()
{
	Super::Init();

	TArray<int32> IntArray;

	IntArray.Init(10, 5); // 초기화 : [10,10,10,10,10]
	
	// 1. 삽입
	TArray<FString> StrArray;
	StrArray.Add(TEXT("Hello"));		// Add,Push : push_back, 임시변수 생성 후, 배열에 복사하는 방식
	StrArray.Emplace(TEXT("World"));	// Emplace : 배열 안에서 직접 생성
	// 효율 차이는 적음
	FString Arr[] = { TEXT("of"), TEXT("Tomorrow") };
	StrArray.Append(Arr, UE_ARRAY_COUNT(Arr));	// Append : 다수의 원소를 배열로 추가
	StrArray.AddUnique(TEXT("!"));				// AddUnique : FindOrAdd방식의 Add
	StrArray.Insert(TEXT("Brave"), 1);			// Insert : 추가할 위치를 지정가능

	// 2. 반복
	// 공식문서에선 C++ 범위 기능 for를 추천함
	// 또한 반복자 생성도 가능
	FString JoinedStr;
	for (auto& Str : StrArray)
	{
		JoinedStr += Str;
		JoinedStr += TEXT(" ");
	}
	for (auto It = StrArray.CreateConstIterator(); It; ++It)
	{
		// It을 활용...
	}

	// 3. 정렬
	StrArray.Sort(); // 퀵정렬, 숫자는 오름차순, FString은 대소구분없이 사전식 비교
	StrArray.Sort([](const FString& A, const FString& B) {
		return A.Len() < B.Len();
		});
	StrArray.HeapSort(); // 힙정렬, Sort와 방식은 동일하며, 알고리즘만 힙정렬 채택
	StrArray.StableSort(); // '기준'이 같은 요소들은, 정렬 이전의 순서로 보장해줌.

	// 4. 쿼리
	StrArray.Num();										// 원소 개수 확인, int32형 반환
	StrArray.IsValidIndex(3);							// 인덱스 유효성 검사
	FString WantToFind = StrArray[2];					// 배열처럼 접근 가능

	StrArray.Contains(TEXT("Hello"));					// 존재 여부 확인
	int32 FindIdx = StrArray.Find(TEXT("Brave"));		// 위치 반환
	
	FString* FoundPtr = StrArray.FindByPredicate([](const FString & Item) {
		return Item.StartsWith(TEXT("H"));
	});	// FindByPredicate : 조건 기반 탐색, []로 조건 걸고, 조건에 맞는 첫 번째 포인터 반환

	// 5. 제거
	if (StrArray.IsValidIndex(3))
	{
		StrArray.RemoveAt(3);			// RemoveAt : 인덱스 기반 제거, 느림
	}
	StrArray.Remove(TEXT("Hello"));				// Remove : 해당 값 모두 제거
	StrArray.RemoveAll([](FString val) {});		// RemoveAll : 조건 만족 값 모두 제거

	// 제거 - Swap계열
	// Swap 계열은 삭제 후, 맨 마지막 원소를 삭제 위치로 이동시키는 방식
	// 순서가 섞이지만, 속도가 매우 빨라, 순서가 중요치 않으면 사용하는게 좋음
	StrArray.RemoveAtSwap(3);		// REmoveAtSwap : 삭제 후, 맨 마지막 원소를 이동시켜 채움
	StrArray.RemoveAllSwap([](FString val) {	// RemoveAllSwap : RemoveAll + Swap방식
		return val.Contains("o");
		}); 

	StrArray.Empty();							// 전부 제거
}

void USXGameInstance::Shutdown()
{
	Super::Shutdown();

	UE_LOG(LogTemp, Log, TEXT("USXGameInstace::ShutDown() has been called!"));
}
