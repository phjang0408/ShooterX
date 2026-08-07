// Fill out your copyright notice in the Description page of Project Settings.


#include "SXGameInstance.h"	// Game/을 앞에 지워야 하는 이유 : 같은 폴더에 있기 때문, 
// 아니면 Build.cs에 PublicIncludePaths.AddRange로 상대경로를 추가해주면 된다.

USXGameInstance::USXGameInstance()
{
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
}

void USXGameInstance::Shutdown()
{
	Super::Shutdown();

	UE_LOG(LogTemp, Log, TEXT("USXGameInstace::ShutDown() has been called!"));
}
