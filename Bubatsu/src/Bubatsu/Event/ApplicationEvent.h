#pragma once

#include "Event.h"


namespace Bubatsu
{
	class BUBATSU_API ApplicationTickedEvent : public Event
	{
	public:
		ApplicationTickedEvent() {}

		EVENT_CLASS(ApplicationTicked)
		EVENT_CATEGORY(EventCategoryApplication)
	};
	
	class BUBATSU_API ApplicationUpdatedEvent : public Event
	{
	public:
		ApplicationUpdatedEvent() {}

		EVENT_CLASS(ApplicationUpdated)
		EVENT_CATEGORY(EventCategoryApplication)
	};

	class BUBATSU_API ApplicationRenderedEvent : public Event
	{
	public:
		ApplicationRenderedEvent() {}

		EVENT_CLASS(ApplicationRendered)
		EVENT_CATEGORY(EventCategoryApplication)
	};
}
