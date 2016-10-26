/*
 *
 * Copyright (c) 2016 Nest Labs, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef __wpantund__SpinelNCPTaskSendCommand__
#define __wpantund__SpinelNCPTaskSendCommand__

#include "SpinelNCPTask.h"
#include "SpinelNCPInstance.h"

using namespace nl;
using namespace nl::wpantund;

namespace nl {
namespace wpantund {

class SpinelNCPTaskSendCommand : public SpinelNCPTask
{
public:

	class Factory {
	public:
		friend class SpinelNCPTaskSendCommand;

		Factory(SpinelNCPInstance* instance);

		Factory& set_callback(const CallbackWithStatusArg1 &cb);
		Factory& set_callback(const CallbackWithStatus &cb);
		Factory& add_command(const Data& command);
		Factory& set_timeout(int timeout);
		Factory& set_reply_format(const std::string& packed_format);
		Factory& set_lock_property(int lock_property = SPINEL_PROP_THREAD_ALLOW_LOCAL_NET_DATA_CHANGE);

		boost::shared_ptr<SpinelNCPTask> finish(void);

	private:
		SpinelNCPInstance* mInstance;
		CallbackWithStatusArg1 mCb;
		std::list<Data> mCommandList;
		int mTimeout;
		std::string mReplyFormat;
		int mLockProperty;
	};

	SpinelNCPTaskSendCommand(const Factory& factory);

	virtual int vprocess_event(int event, va_list args);

private:

	std::list<Data> mCommandList;
	std::list<Data>::const_iterator mCommandIter;
	int mLockProperty;
	std::string mPackedFormat;
	int mRetVal;
	boost::any mReturnValue;
};

}; // namespace wpantund
}; // namespace nl


#endif /* defined(__wpantund__SpinelNCPTaskSendCommand__) */