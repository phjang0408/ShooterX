// SXGameInstance.cpp

#include "SXGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

USXGameInstance::USXGameInstance()
{
	Name = TEXT("SXGameInstance's Class Default Object");		
}

void USXGameInstance::Init()	//PIE이후에 동작!
{
	Super::Init();


	// 4. [리플렉션]
	// 컴파일타임 클래스와 런타임 클래스가 다를까?
	UClass* CompiletimeClassInfo = StaticClass(); // 앞에 this->가 생략된 의미, 즉 
	UClass* RuntimeClassInfo = GetClass();
	checkf(CompiletimeClassInfo != RuntimeClassInfo, TEXT("CompiletimeClassInfo != RuntimeClassInfo"));
	// 뒤에 '블루프린트 클래스'로 게임 인스턴스를 정하게 되면 ==은 터지게 됨 -> 즉 다르게 됨
	// 언리얼 C++ 클래스 --> 컴파일 클래스 == 런타임 클래스
	// 블루프린트 에셋 클래스 --> 컴파일 클래스 != 런타임 클래스
	UE_LOG(LogTemp, Log, TEXT("CompiletimeClassInfo->GetName(): %s"), *CompiletimeClassInfo->GetName());
	UE_LOG(LogTemp, Log, TEXT("RuntimeClassInfo->GetName() : %s"), *RuntimeClassInfo->GetName());

	Name = TEXT("SXGameInstance's Object");
		// Init()은 언리얼 에디터가 실행된 이후에 호출
		// 이 시점은 USXGameInstance 클래스의 CDO가 생성된 이후이므로
		// 이 떄의 Name 속성 수정은, CDO가 아닌,
		// USXGameInstance 클래스 인스턴스의 Name속성 수정에 해당
	UE_LOG(LogTemp, Log, TEXT("USXGameInstance::Name %s"), *(RuntimeClassInfo->GetDefaultObject<USXGameInstance>()->Name));
	// ㄴ->리플렉션!
	UE_LOG(LogTemp, Log, TEXT("USXGameInstance::Name %s"), *Name);
	// ㄴ-> 그냥 자기 변수 가져오는거
}

void USXGameInstance::Shutdown()
{
	Super::Shutdown();

	UE_LOG(LogTemp, Log, TEXT("USXGameInstace::ShutDown() has been called!"));
}
