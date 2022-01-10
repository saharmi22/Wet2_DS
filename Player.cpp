//
// Created by sahar on 09/01/2022.
//

#include "Player.h"

    Player::Player(int id, int score, int group_id) : id(id), level(0), score(score), group_id(group_id){}

    int Player::getId() const {
        return id;
    }

    int Player::getLevel() const {
        return level;
    }

    int Player::getScore() const {
        return score;
    }

    int Player::getGroupId() const {
        return group_id;
    }

    void Player::addToLevel(int increase_level) {
        Player::level += increase_level;
    }

    void Player::setScore(int score_) {
        Player::score = score_;
    }

    void Player::setGroupId(int groupId) {
        group_id = groupId;
    }