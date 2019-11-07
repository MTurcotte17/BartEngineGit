#ifndef BART_ENTITY_H
#define BART_ENTITY_H

#include <IGraphic.h>
#include <EKeys.h>
#include <ICollision.h>

namespace bart
{
    class Entity
    {
    public:
        virtual ~Entity() = default;

        virtual void Update(float aDeltaTime);
        virtual void Draw();

        virtual bool CanDraw() = 0;
        virtual bool CanUpdate() = 0;
        virtual void Start() = 0;
        virtual void Destroy() = 0;

        bool IsActive() const { return m_IsActive; }
        void SetActive(const bool aEnabled) { m_IsActive = aEnabled; }

        std::string GetName() const { return m_Name; }
        void SetName(const std::string& aName) { m_Name = aName; }

    protected:
        static IGraphic& GetGraphics();
        static ICollision& GetCollision();

        static bool IsKeyDown(EKeys aKey);
        static void AddEntity(const std::string& aId, Entity* aEntity);
        static Entity* FindEntity(const std::string& aId);
        static void Load(const std::string& aId);

        bool m_IsActive{true};
        std::string m_Name;
    };
}

#endif
