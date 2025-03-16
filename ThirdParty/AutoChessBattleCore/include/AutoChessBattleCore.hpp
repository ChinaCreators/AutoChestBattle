#pragma once
#include <cstdint>
#include <functional>
namespace AutoChessBattleCore
{
	enum class CardType
	{
		Minion,
		Spell,
	};

	struct CardView
	{
		uint32_t m_Id = 0;
		CardType m_Type = CardType::Minion;
		int32_t m_Attack = 0;
		int32_t m_Health = 0;
		uint32_t m_Traits = 0;
		const char* m_Name = nullptr;
		const char* m_ImagePath = nullptr;
		const char* m_Description = nullptr;
		const char* m_Details = nullptr;
		const char* m_Tags = nullptr;
		bool m_IsFrozen = false;
		bool m_IsGolden = false;
	};

	struct MinionView
	{
		uint32_t m_Id = 0;
		int32_t m_Attack = 0;
		int32_t m_Health = 0;
		uint32_t m_Traits = 0;
		const char* m_Name = nullptr;
		const char* m_ImagePath = nullptr;
		const char* m_Description = nullptr;
		const char* m_Details = nullptr;
		const char* m_Tags = nullptr;
		bool m_IsGolden = false;
	};

	struct PlayerCombatRecord
	{
		uint32_t m_EnemyId = 0;
		int32_t m_Damage = 0;
	};

	struct PlayerView
	{
		uint32_t m_Id = 0;
		uint32_t m_Health = 0;
		uint32_t m_Armor = 0;
		uint32_t m_ShopLevel = 0;
		const char* m_Name = nullptr;
		const char* m_ImagePath = nullptr;
		const char* m_Description = nullptr;
		uint32_t m_ContinueWinCount = 0;
		uint32_t m_GoldenMinionCount = 0;
		PlayerCombatRecord m_LatestCombatRecord[3];
	};

	/*
	version 1.0 基本的游戏玩法，暂时不考虑英雄技能，后续可能会加入
	*/
	class AutoChessBattleCoreInterface
	{
	public:
		virtual ~AutoChessBattleCoreInterface() = default;

		virtual bool IsPlayerAlive() const = 0;
		virtual PlayerView GetPlayer() const = 0;
		virtual uint32_t GetPlayerGold() const = 0;
		virtual uint32_t GetPlayerInitialGold() const = 0;

		virtual void VisitPlayerRanking(const std::function<void(const PlayerView&)>& visitor) const = 0;

		virtual bool CanIncreaseShopLevel() const = 0;
		virtual bool IncreaseShopLevel() = 0;

		virtual void VisitShopCards(const std::function<void(const CardView&)>& visitor) const = 0;
		virtual bool CanRefreshShopCards() const = 0;
		virtual bool RefreshShopCards() = 0;
		virtual bool ToggleShopCardsFreeze() = 0;
		virtual bool CanBuyShopCard(uint32_t card_id) const = 0;
		virtual bool BuyShopCard(uint32_t card_id) = 0;

		virtual void VisitPlayerCards(const std::function<void(const CardView&)>& visitor) const = 0;
		virtual bool CanUsePlayerCard(uint32_t card_id, int32_t position) const = 0;
		virtual bool UsePlayerCard(uint32_t card_id, int32_t position) = 0;

		virtual void VisitPlayerMinions(const std::function<void(const MinionView&)>& visitor) const = 0;
		virtual bool CanSellPlayerMinion(uint32_t minion_id) const = 0;
		virtual bool SellPlayerMinion(uint32_t minion_id) = 0;
		virtual bool CanMovePlayerMinion(uint32_t minion_id, int32_t position) const = 0;
		virtual bool MovePlayerMinion(uint32_t minion_id, int32_t position) = 0;

		// 返回秒
		virtual float GetPlayerPreparationRemainTime() const = 0;
		// 后续也许可以让玩家选择是否准备好
		virtual bool CanStartCombatRound() const = 0;
		virtual void TickCombatRound() = 0;
		virtual bool IsCombatRoundFinished() const = 0;
		// 返回战斗结果，0表示平局，正数代表我方对敌方造成的攻击，负数代表敌方对我方造成的攻击
		virtual int32_t GetCombatRoundResult() const = 0;
		virtual PlayerView GetEnemyPlayer() const = 0;
		virtual void VisitEnemyMinions(const std::function<void(const MinionView&)>& visitor) const = 0;

	};
}