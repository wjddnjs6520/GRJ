#include "Battle/BattleManager.h"

#include "TempActor.h"
#include "Battle/SkillManager.h"
#include "Character/GRJCharacterBase.h"

UBattleManager::UBattleManager()
{
    UE_LOG(LogTemp, Log, TEXT("[BattleManager] 생성"));

    //턴제 전투 스킬 사용 매니저 추가
    CurrentSkillManager = NewObject<USkillManager>(this);
    CurrentSkillManager->SettingBattleManager(this);
    
}

void UBattleManager::BattleStart()
{
    UE_LOG(LogTemp, Log, TEXT("[BattleManager] BattleStart 호출"));

    if (!TempActor)
    {
        UE_LOG(LogTemp, Error, TEXT("[BattleManager] TempActor가 nullptr"));
        return;
    }

    PlayerCharacters = TempActor->PlayerTeam;
    EnemyCharacters = TempActor->EnemyTeam;

    UE_LOG(LogTemp, Log,
        TEXT("[BattleManager] 전투 참여자 설정 - Player: %d, Enemy: %d"),
        PlayerCharacters.Num(), EnemyCharacters.Num());

    if (CheckEndBattle())
    {
        UE_LOG(LogTemp, Warning, TEXT("[BattleManager] 전투 시작 불가"));
        BattleEnd();
        return;
    }

    MakeTurnOder();
    StartTurn();
}

void UBattleManager::StartTurn()
{
    UE_LOG(LogTemp, Log,
        TEXT("[BattleManager] StartTurn - Index: %d, TurnOrder: %d"),
        CurrentTurnIndex, TurnOrder.Num());

    if (CheckEndBattle())
    {
        UE_LOG(LogTemp, Log, TEXT("[BattleManager] 전투 종료 조건 충족"));
        BattleEnd();
        return;
    }

    if (CurrentTurnIndex >= TurnOrder.Num())
    {
        UE_LOG(LogTemp, Log, TEXT("[BattleManager] 라운드 종료, 턴 순서 재생성"));
        MakeTurnOder();
    }

    AGRJCharacterBase* Character = CurrentTurnCharacter();

    if (!Character)
    {
        UE_LOG(LogTemp, Error, TEXT("[BattleManager] 현재 턴 캐릭터가 nullptr"));
        return;
    }

    UE_LOG(LogTemp, Log,
        TEXT("[BattleManager] 턴 시작 캐릭터: %s"),
        *Character->GetName());

    Character->SetCurrentBattleManager(this);
    Character->StartCharacterTurn();
}

void UBattleManager::NextTurn()
{
    UE_LOG(LogTemp, Log,
        TEXT("[BattleManager] NextTurn 호출 - 이전 Index: %d"),
        CurrentTurnIndex);

    CurrentTurnIndex++;

    StartTurn();
}

AGRJCharacterBase* UBattleManager::CurrentTurnCharacter()
{
    if (!TurnOrder.IsValidIndex(CurrentTurnIndex))
    {
        UE_LOG(LogTemp, Warning,
            TEXT("[BattleManager] 유효하지 않은 턴 인덱스: %d"),
            CurrentTurnIndex);

        return nullptr;
    }

    return TurnOrder[CurrentTurnIndex];
}

AGRJCharacterBase* UBattleManager::EnemyCharacter(int32 TargetNum)
{
    if (!EnemyCharacters.IsValidIndex(TargetNum))
    {
        UE_LOG(LogTemp, Warning,
            TEXT("[BattleManager] 잘못된 적 대상 인덱스: %d"),
            TargetNum);

        return nullptr;
    }

    AGRJCharacterBase* Target = EnemyCharacters[TargetNum];

    if (Target)
    {
        UE_LOG(LogTemp, Log,
            TEXT("[BattleManager] 적 대상 조회: Index=%d, Name=%s"),
            TargetNum, *Target->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning,
            TEXT("[BattleManager] 적 대상이 nullptr: Index=%d"),
            TargetNum);
    }

    return Target;
}

int32 UBattleManager::GetEnemyCount() const
{
    return EnemyCharacters.Num();
}

int32 UBattleManager::GetPlayerCount() const
{
    return PlayerCharacters.Num();
}

void UBattleManager::MakeTurnOder()
{
    UE_LOG(LogTemp, Log, TEXT("[BattleManager] 턴 순서 생성 시작"));

    TurnOrder.Empty();

    TurnOrder.Append(PlayerCharacters);
    TurnOrder.Append(EnemyCharacters);

    TurnOrder.Sort([](const AGRJCharacterBase& A, const AGRJCharacterBase& B)
    {
        return A.GetSpeed() > B.GetSpeed();
    });

    CurrentTurnIndex = 0;

    for (int32 i = 0; i < TurnOrder.Num(); i++)
    {
        if (TurnOrder[i])
        {
            UE_LOG(LogTemp, Log,
                TEXT("[BattleManager] 턴 순서 [%d]: %s, Speed=%.1f"),
                i, *TurnOrder[i]->GetName(), TurnOrder[i]->GetSpeed());
        }
        else
        {
            UE_LOG(LogTemp, Warning,
                TEXT("[BattleManager] 턴 순서 [%d] 캐릭터가 nullptr"),
                i);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("[BattleManager] 턴 순서 생성 완료"));
}

bool UBattleManager::CheckEndBattle()
{
    const bool bIsBattleEnd =
        PlayerCharacters.Num() == 0 || EnemyCharacters.Num() == 0;

    UE_LOG(LogTemp, Log,
        TEXT("[BattleManager] 전투 종료 검사 - Player: %d, Enemy: %d, End: %s"),
        PlayerCharacters.Num(),
        EnemyCharacters.Num(),
        bIsBattleEnd ? TEXT("true") : TEXT("false"));

    return bIsBattleEnd;
}

void UBattleManager::BattleEnd()
{
    UE_LOG(LogTemp, Log, TEXT("[BattleManager] BattleEnd 호출"));

    PlayerCharacters.Empty();
    EnemyCharacters.Empty();
    TurnOrder.Empty();
    CurrentTurnIndex = 0;

    UE_LOG(LogTemp, Log, TEXT("[BattleManager] 전투 데이터 초기화 완료"));
}