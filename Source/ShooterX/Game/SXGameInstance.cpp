// SXGameInstance.cpp

#include "SXGameInstance.h"
#include "Example/SXFlyable.h"
#include "Example/SXEagle.h"
#include "Example/SXPigeon.h"

USXGameInstance::USXGameInstance()
{	
}

void USXGameInstance::Init()
{
	Super::Init();
	
	// Serialaize : Pigeon76(객체) -Serialize(FMemoryArchive객체)-> 메모리 버퍼 -파일 아카이브(IFileManager)-> .bin
	// DeSerialize : 반대

	// 0. 새로운 객체 생성
	USXPigeon* Pigeon76 = NewObject<USXPigeon>();
	Pigeon76->SetPigeonName(TEXT("Pigeon76"));
	Pigeon76->SetPigeonID(76);
	UE_LOG(LogTemp, Log, TEXT("[Pigeon76] Name : %s, ID : %d"), *Pigeon76->GetPigeonName(), Pigeon76->GetPigeonID());

	// 1. 경로 지정
	// -> 경로에는 파일 경로 + 파일 이름을 Combine -> MakeStandardFilename으로 가공!
	const FString SavedDirectoryPath = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));
	const FString SavedFileName(TEXT("SerializedPigeon76Data.bin"));
	FString AbsoluteFilePath = FPaths::Combine(*SavedDirectoryPath, *SavedFileName);
	FPaths::MakeStandardFilename(AbsoluteFilePath);

	// 2. Serialize 단계
	// 2.1 객체 <-> 메모리 버퍼 : FMemoryWriter/Reader로 생성한 아카이브 객체
	TArray<uint8> BufferForWriter;						// 한 칸 uint8짜리 배열(버퍼역할)생성
	FMemoryWriter MemoryWriterArchive(BufferForWriter);	// 이 버퍼를 인자로, 아카이브 객체 생성(작업공간을 할당)
	Pigeon76->Serialize(MemoryWriterArchive);			// 이 아카이브 객체로, 우리가 override한 Serialize호출

	// 2.2 메모리 버퍼 <-> 디스크 파일 : IFileManager로 생성한 아카이브 객체
	TUniquePtr<FArchive> WriterArchive = TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*AbsoluteFilePath));
	if (WriterArchive != nullptr) {
		*WriterArchive << BufferForWriter;	// 아카이브 객체가 메모리 버퍼를 <<로 받아와 디스크 파일 작성
		WriterArchive->Close();
		WriterArchive = nullptr; // 이번엔 유니크 ptr로 써서, delete대신 nullptr
	}

	// 3. DeSerialize단계
	// 3.1 유니크포인터 파일 아카이브로, 파일 데이터를 버퍼로 가져옴
	TArray<uint8> BufferForReader;
	TUniquePtr<FArchive> ReaderArchive = TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*AbsoluteFilePath));
	if (ReaderArchive != nullptr)
	{
		*ReaderArchive << BufferForReader;
		ReaderArchive->Close();
		ReaderArchive = nullptr;
	}

	// 작성된 버퍼를, FMemoryReader객체 생성의 인자로 전달.
	// 이 생성된 아카이브 객체를 Serialize() 하여 객체로 전달.
	FMemoryReader MemoryReaderArchive(BufferForReader);
	USXPigeon* ClonedPigeon76 = NewObject<USXPigeon>();
	ClonedPigeon76->Serialize(MemoryReaderArchive);
	UE_LOG(LogTemp, Log, TEXT("[ClonedPigeon76] Name : %s, ID : %d"), *ClonedPigeon76->GetPigeonName(), ClonedPigeon76->GetPigeonID());

}

void USXGameInstance::Shutdown()
{
	Super::Shutdown();

	UE_LOG(LogTemp, Log, TEXT("USXGameInstace::ShutDown() has been called!"));
}
