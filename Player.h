//
// Created by sahar on 09/01/2022.
//

#ifndef WET2_DS_PLAYER_H
#define WET2_DS_PLAYER_H

class Player {
private:

    int id;
    int level;
    int score;
    int group_id;

public:

    Player(int id, int score, int group_id);
    int getId() const;
    int getLevel() const;
    int getScore() const;
    int getGroupId() const;
    void addToLevel(int increase_level);
    void setScore(int score_);
    void setGroupId(int groupId);

};


#endif //WET2_DS_PLAYER_H
