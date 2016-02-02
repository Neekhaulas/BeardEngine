#pragma once

class Hero
{
public:
	Hero() : ad(0), ap(0), hp(0), mp(0), armor(0), mr(0), cdr(0), moveSpeed(0), attackSpeed(0), regenHP(0), regenMP(0),
		ad_per_level(0), ap_per_level(0), hp_per_level(0), mp_per_level(0), armor_per_level(0), mr_per_level(0), cdr_per_level(0), moveSpeed_per_level(0), attackSpeed_per_level(0), regenHP_per_level(0), regenMP_per_level(0) {};
	void setAD(float ad) { this->ad = ad; };
	void setAP(float ap) { this->ap = ap; };
	void setHP(float hp) { this->hp = hp; };
	void setMP(float mp) { this->mp = mp; };
	void setArmor(float armor) { this->armor = armor; };
	void setMR(float mr) { this->mr = mr; };
	void setCDR(float cdr) { this->cdr = cdr; };
	void setMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; };
	void setAttackSpeed(float attackSpeed) { this->attackSpeed = attackSpeed; };
	void setRegenHP(float regenHP) { this->regenHP = regenHP; };
	void setRegenMP(float regenMP) { this->regenMP = regenMP; };

	void setADPerLevel(float ad_per_level) { this->ad_per_level = ad_per_level; };
	void setAPPerLevel(float ap_per_level) { this->ap_per_level = ap_per_level; };
	void setHPPerLevel(float hp_per_level) { this->hp_per_level = hp_per_level; };
	void setMPPerLevel(float mp_per_level) { this->mp_per_level = mp_per_level; };
	void setArmorPerLevel(float armor_per_level) { this->armor_per_level = armor_per_level; };
	void setMRPerLevel(float mr_per_level) { this->mr_per_level = mr_per_level; };
	void setCDRPerLevel(float cdr_per_level) { this->cdr_per_level = cdr_per_level; };
	void setMoveSpeedPerLevel(float moveSpeed_per_level) { this->moveSpeed_per_level = moveSpeed_per_level; };
	void setAttackSpeedPerLevel(float attackSpeed_per_level) { this->attackSpeed_per_level = attackSpeed_per_level; };
	void setRegenHPPerLevel(float regenHP_per_level) { this->regenHP_per_level = regenHP_per_level; };
	void setRegenMPPerLevel(float regenMP_per_level) { this->regenMP_per_level = regenMP_per_level; };

	float getAD() { return ad; }
	float getAP() { return ap; }
	float getHP() { return hp; }
	float getMP() { return mp; }
	float getArmor() { return armor; }
	float getMR() { return mr; }
	float getCDR() { return cdr; }
	float getMoveSpeed() { return moveSpeed; }
	float getAttackSpeed() { return attackSpeed; }
	float getRegenHP() { return regenHP; }
	float getRegenMP() { return regenMP; }

	float getADPerLevel() { return ad_per_level; }
	float getAPPerLevel() { return ap_per_level; }
	float getHPPerLevel() { return hp_per_level; }
	float getMPPerLevel() { return mp_per_level; }
	float getArmorPerLevel() { return armor_per_level; }
	float getMRPerLevel() { return mr_per_level; }
	float getCDRPerLevel() { return cdr_per_level; }
	float getMoveSpeedPerLevel() { return moveSpeed_per_level; }
	float getAttackSpeedPerLevel() { return attackSpeed_per_level; }
	float getRegenHPPerLevel() { return regenHP_per_level; }
	float getRegenMPPerLevel() { return regenMP_per_level; }

private:
	float ad, ap, hp, mp, armor, mr, cdr, moveSpeed, attackSpeed, regenHP, regenMP,
		ad_per_level, ap_per_level, hp_per_level, mp_per_level, armor_per_level, mr_per_level, cdr_per_level, moveSpeed_per_level, attackSpeed_per_level, regenHP_per_level, regenMP_per_level;

};