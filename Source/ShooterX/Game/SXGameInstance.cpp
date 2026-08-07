// Fill out your copyright notice in the Description page of Project Settings.


#include "SXGameInstance.h"	// Game/을 앞에 지워야 하는 이유 : 같은 폴더에 있기 때문, 
// 아니면 Build.cs에 PublicIncludePaths.AddRange로 상대경로를 추가해주면 된다.
#include "Kismet/KismetSystemLibrary.h"

USXGameInstance::USXGameInstance()
{
	// 1. [기본 로그]
	// 언리얼의 로그 : 로그 카테고리, 로그 수준, 형식문자열(c언어 printf)	, 인자
	UE_LOG(LogTemp, Log, TEXT("USXGameInstance() has been called!"));

	// 실제 찍어보면, 로그에서 검색 가능
	// 근데 두 번 나옴 -> 즉, Play In Editor를 누르기 전에도 검색이 됨.
	// 이는 Class Default Object가 생성될 떄 호출된 것	
}

void USXGameInstance::Init()
{
	// Super는 부모 클래스 이름을 재정의, 즉 부모 클래스 이름과 동일
		// 엔진 업데이트 루틴을 지키기 위해서, 언리얼 엔지니어가 작성한 코드가 먼저 실행되게끔 하기 위함.
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("USXGameInstance::Init() has been called!"));


	// 2. [UKismet로그]
	// UE_LOG()는 Output Log에서만 로그를 볼 수 있음.
	// 간혹 게임 화면에 로그를 띄워서 보고 싶을 때 사용 -> 멀티플레이면, 창이 여러 개 띄우기도 하고..
	// 이다만 배포 전에는 꼭 주석처리 해야함

	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("[Kismet] USXGameInstance::Init()!"));

	// UKismetSystemLibrary::PrintString() 함수의 첫 매개변수 이름은 "WorldContextObject" 
	// Context란, 문맥상 "~될만한거" 라고 생각하면 좋음. 여기서는 "월드 객체를 만들만한 거"라고 해석.
	// 따라서 GetWorld()를 통해서 진짜 World 객체를 넘겨줘도 되지만
	// this(USGameInstance 객체)를 전달해서 this가 속한 월드 객체를 구하게끔 해도된다는 뜻.


	// 3. [유효성검사] 3가지 방법
	UWorld* WorldInstance = GetWorld(); 
	
	// 1. IsValid : false일 수도 있음
	// 런타임 중, 1 객체 포인터가 유효한 지(c++에서의 nullptr 검사, asult)
	// 거기에 더해, 2 Pending Kill, 3 GC대상인지 까지 모두 체크해줌
	
	if (IsValid(WorldInstance) == true) {
		// 이런 식으로도 할 순 있지만, 만에하나 WorldInstance 객체가 유효하지 않다면?
		// 아무런 로직이 돌지 않으므로 다른 팀원은 잘못된건지 단박에 알아채지 못할 수도 있음.
		// WorldInstance 객체가 없다는건 큰 문제이므로 이럴 때 checkf()를 활용.
		UKismetSystemLibrary::PrintString(WorldInstance, TEXT("IsValid is true!!"));
	}

	// 2. checkf : false면 안됨, false일 리 없음
	// 참이면, 실행 X  || 조건식이 거짓이면, 크래시 발생시킴 -> 비정상 상황 감지!
	// 크래시 발생 시, 다시 빌드해야 함.
	// check에  디버깅 정보를 포함한 버전 = checkf
	checkf(IsValid(WorldInstance) == true, TEXT("Using checkf"));

	// 3. ensureMsgf : checkf에서, 프로그램 종료까지는 아니라면
	// 마찬가지로 참이면, 실행 X
	// '복구 로직'을 작성해야 하는 경우 ensure를 사용
	// ensure함수에 디버깅 정보를 포함한 버전 = ensureMsgf
	ensureMsgf(IsValid(WorldInstance) == true, TEXT("Using ensureMsgf"));
}

void USXGameInstance::Shutdown()
{
	Super::Shutdown();

	UE_LOG(LogTemp, Log, TEXT("USXGameInstace::ShutDown() has been called!"));
}
