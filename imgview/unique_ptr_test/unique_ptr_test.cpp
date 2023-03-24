#include <memory>

struct Taz
{
	void Do()
	{
		printf("Something\n");
	}
};

class Foo
{
public:
	void Assign(std::unique_ptr<Taz>&& t)
	{
		m_t = std::move(t);
	}

	void Do() { m_t->Do(); }

private:
	std::unique_ptr<Taz> m_t;
};

int main()
{
	std::shared_ptr<Foo> bar(new Foo());
	std::unique_ptr<Taz> baz = std::make_unique<Taz>();
	bar->Assign(std::move(baz));

	bar->Do();

	return 0;
}
