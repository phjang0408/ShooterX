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

	// [1. TCHAR와 FString]
	TCHAR ArrayOfTChar[] = TEXT("Hello, Unreal!");
		// UTF-16 인코딩 문자열을 저장하는, '언리얼 표준 문자 자료형'이 TCHAR
		// TCHAR 문자열을 생성하기 위한 매크로가 TEXT()

	FString String0 = ArrayOfTChar;
		// 문자열을 조금 더 자유롭게 조작(인덱싱 등)하고 싶다면, TCHAR 배열 대신, FString사용
		// TCHAR배열을 Wrapping한 핼퍼 클래스가 FString
	FString String1 = FString(TEXT("Hello,Unreal!"));		// FString을 바로 만드는 법(TCHAR거치지않고)
	UE_LOG(LogTemp, Log, TEXT("String1: %s"), *String1);	// FString에 *을 붙여야 TCHAR형태로 사용 가능!


	const TCHAR* PtrToTChar = *String1;						// FString + * 이 바로 TCHAR*
	TCHAR* RawptrToChar = String1.GetCharArray().GetData(); // const를 깨는 방법(참고만)

	// [2. FString 활용]
	// Contains로 포함여부 확인 가능(bool)
	// ESearchCase::IgnoreCase -> 대소문자 무시
	if (String1.Contains(TEXT("unreal"), ESearchCase::IgnoreCase) == true)
	{
		// Find함수 -> 그 인덱스 시작지점 반환
		int32 Index = String1.Find(TEXT("unreal"), ESearchCase::IgnoreCase);
		// Mid함수 -> 인덱스부터 마지막까지 자르는 함수
		FString FoundedString = String1.Mid(Index);

		UE_LOG(LogTemp, Log, TEXT("Founded String : %s"), *FoundedString);
	}

	// [3. int32, float과 FString간의 상호변환]
	int32 IntValue = 7;
	float FloatValue = 3.141592f;

	// PrintF -> c언어 printf와 거진 유사
	FString StringWithNumbers = FString::Printf(TEXT("int32: %d, float: %f"), IntValue, FloatValue);
	UE_LOG(LogTemp, Log, TEXT("StringWithNumber : %s"), *StringWithNumbers);

	// int32 -> FString : FromInt
	FString IntString = FString::FromInt(IntValue);
	UE_LOG(LogTemp, Log, TEXT("IntString : %s"), *IntString);

	// float -> FString : SanitizeFloat
	FString FloatString = FString::SanitizeFloat(FloatValue);
	UE_LOG(LogTemp, Log, TEXT("FloatString : %s"), *FloatString);

	// FCString은 C언어 문자열 라이브러리 함수들을 제공함(atoi, strcpy 등)
	// FString -> int32 : Atoi
	int32 IntValueFromString = FCString::Atoi(*IntString);
	UE_LOG(LogTemp, Log, TEXT("IntValueFromString : %d"), IntValueFromString);

	// FString -> float : Atof
	float FloatValueFromString = FCString::Atof(*FloatString);
	UE_LOG(LogTemp, Log, TEXT("FloatValueFromString : %f"), FloatValueFromString);
}

void USXGameInstance::Shutdown()
{
	Super::Shutdown();

	UE_LOG(LogTemp, Log, TEXT("USXGameInstace::ShutDown() has been called!"));
}
