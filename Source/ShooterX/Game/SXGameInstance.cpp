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
	// 0. 새로운 객체 생성
	USXPigeon* Pigeon76 = NewObject<USXPigeon>();
	Pigeon76->SetPigeonName(TEXT("Pigeon76"));
	Pigeon76->SetPigeonID(76);
	UE_LOG(LogTemp, Log, TEXT("[Pigeon76] Name: %s, ID: %d"), *Pigeon76->GetPigeonName(), Pigeon76->GetPigeonID());

	// 1. 절대경로 생성
	const FString SavedDirectoryPath = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));
	const FString SavedFileName = TEXT("SerializedPigeon76JsonData.txt");
	FString AbsolutePath = FPaths::Combine(*SavedDirectoryPath, *SavedFileName);
	FPaths::MakeStandardFilename(AbsolutePath);

	// [2. JSON 객체로 변환]
	// FJsonObjectConverter::UStructToJsonObject() : 구조체를 Json객체로 만드는 함수 - UStructToJsonObjectString으로 String으로 바로도 가능
	// 인자는 (클래스_타입, 객체, Out될 FJsonObject)이며, 마지막 FJson인자는 빼도 된다.
	TSharedRef<FJsonObject> Pigeon76JsonObject = MakeShared<FJsonObject>();
	FJsonObjectConverter::UStructToJsonObject(Pigeon76->GetClass(), Pigeon76, Pigeon76JsonObject);

	// 3. Writer 준비과정
	FString WritedJsonString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriterArchive = TJsonWriterFactory<TCHAR>::Create(&WritedJsonString);

	// 4. [직렬화]
	if (FJsonSerializer::Serialize(Pigeon76JsonObject, JsonWriterArchive) == true)
	{
		// 5. 완성된 JSON 문자열을 파일로 저장 -> FileHelper사용
		FFileHelper::SaveStringToFile(WritedJsonString, *AbsolutePath);
	}



	// [5.JSON문자열 -> FJsonObject]
	// FileHelper를 통해, 문자열에서 Json읽어옴
	FString ReadedJsonString;
	FFileHelper::LoadFileToString(ReadedJsonString, *AbsolutePath);
	USXPigeon* ClonedPigeon76 = NewObject<USXPigeon>();		// 옮겨질 빈 객체

	// 7. 문자열을 읽어들일 Reader 준비
	TSharedRef<TJsonReader<TCHAR>> JsonReaderArchive = TJsonReaderFactory<TCHAR>::Create(ReadedJsonString);

	// [역직렬화]
	TSharedPtr<FJsonObject> ClonedPigeon76JsonObject = nullptr;
	if (FJsonSerializer::Deserialize(JsonReaderArchive, ClonedPigeon76JsonObject) == true)
	{
		// 10. FJsonObject -> UStruct(객체)로 변환
		if (FJsonObjectConverter::JsonObjectToUStruct(ClonedPigeon76JsonObject.ToSharedRef(), ClonedPigeon76->GetClass(), ClonedPigeon76) == true)
		{
			UE_LOG(LogTemp, Log, TEXT("[ClonedPigeon76] Name: %s, ID: %d"), *ClonedPigeon76->GetPigeonName(), ClonedPigeon76->GetPigeonID());
		}
	}
}

void USXGameInstance::Shutdown()
{
	Super::Shutdown();

	UE_LOG(LogTemp, Log, TEXT("USXGameInstace::ShutDown() has been called!"));
}
