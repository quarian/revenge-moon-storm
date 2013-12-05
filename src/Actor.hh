#ifndef MB2_ACTOR_HH
#define MB2_ACTOR_HH

/*
 * Actor.hh
 */

#include "Walker.hh"
#include "Inventory.hh"

class Actor : public Walker {
friend bool ActorTest1(std::ostream&);

public:
    /* Constructor
     *
     * PARAMETERS
     * ==========
     *  Map const&          map that the Actor is placed on
     *  MapBlock*           initial position on the map
     *  float               movement speed (blocks per second)
     *  float               digging power (0.0 if can't dig)
     *  int                 maximum health (also starting health)
     *  float               damage resistance; 0.0 - 1.0
     *  Inventory*          where collected items go -- if nullptr, doesn't collect
     */
    Actor(Map&, MapBlock*, float, float=0.0, int=100, float=0.0, Inventory* =nullptr);
    virtual ~Actor();

    /* Deals/heals damage. takeDamage() returns true if the Actor is still
     * alive after the damage is dealt. */
    virtual bool takeDamage(float);
    virtual bool heal(float);

    /* Getters and other info. */
    int getHealth() const { return health_; }
    int getMaxHealth() const { return maxHealth_; }
    int getVulnerability() const { return vulnerability_; }

    bool isAlive() const { return health_ > 0; }
    bool isDigger() const { return digPower_ > 0; }

    virtual void update(float); // Overridden
    
    void initSprite(Animation const& walking, Animation const& digging, sf::Color);
    
    AnimatedSprite& getSprite();


protected:
    virtual void knock(Direction); // Overridden
    virtual void findTarget(float);
    void dig(float);
    void proceed();

    bool digging_;
    float digPower_;
    int health_;
    int maxHealth_;
    float vulnerability_;
    Inventory* inventory_;
    
    //								void updateSprite(float dt);
    AnimatedSprite spriteDigger_;
};

#endif
