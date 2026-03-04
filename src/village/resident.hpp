#pragma once

#include <random>
#include <memory>
#include <algorithm>
#include <vector>

namespace vsa::village {

class Resident : public std::enable_shared_from_this<Resident>
{
public:
    Resident() = delete;
    explicit Resident(bool is_male, std::size_t age_days);

    virtual ~Resident() = default;

    virtual std::string get_id() = 0;
    virtual std::string get_name() = 0;

    virtual void iterate_impl() = 0;

    virtual void eat() = 0;
    virtual void produce() = 0;

    bool iterate();

    [[nodiscard]] bool is_male() const { return m_is_male; }
    [[nodiscard]] bool is_dead() const { return m_is_dead; }
    [[nodiscard]] std::size_t get_age_days() const { return m_age_days; }
    [[nodiscard]] std::size_t get_age_years() const { return m_age_days / 365; }

    std::size_t get_children_count() {return m_children.size(); }
    bool has_partner() {return m_partner != nullptr; }
    void add_father(std::shared_ptr<Resident> r) { m_father = r; }
    void add_mother(std::shared_ptr<Resident> r) { m_mother = r; }
    void add_parent(std::shared_ptr<Resident> r)
    {
        if (r->is_male()) { m_father = r; }
        else { m_mother = r; }
    }
    void add_partner(std::shared_ptr<Resident> r) { m_partner = r; }
    void add_child(std::shared_ptr<Resident> r) { m_children.push_back(r); }

    void remove_father() { m_father.reset(); }
    void remove_mother() { m_mother.reset(); }
    void remove_partner() { m_partner.reset(); }
    void remove_child(std::shared_ptr<Resident> rc) {
        std::erase_if(m_children, [rc](const std::shared_ptr<Resident>& r) { return r == rc; });
    }

    void remove_relations();

private:
    bool m_is_male = true;
    std::size_t m_age_days = 0;
    float m_death_probability = 0.0f;

    bool m_is_dead = false;

    std::shared_ptr<Resident> m_father = nullptr;
    std::shared_ptr<Resident> m_mother = nullptr;
    std::shared_ptr<Resident> m_partner = nullptr;
    std::vector<std::shared_ptr<Resident>> m_children;
};

} // village