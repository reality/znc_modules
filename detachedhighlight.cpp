/*
* detachedhighlight.cpp
* Forwards notices containing any highlights received in detached channels.
* Copyright (C) Luke Slater (reality) <tinmachin3@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

// This module will send notices of any highlights you receive in
// detached channels.

#include <znc/main.h>
#include <znc/Modules.h>
#include <znc/IRCNetwork.h>
#include <znc/User.h>
#include <znc/Chan.h>
#include <pcrecpp.h>

class CDetachedHighlight : public CModule {

public:
    MODCONSTRUCTOR(CDetachedHighlight) {
    }

    virtual EModRet OnChanMsg(CNick& nick, CChan& channel, CString& sMessage) {
        CString currentNick = m_pNetwork->GetNick();
        pcrecpp::RE re(currentNick);

        if(re.error().length() == 0 && re.PartialMatch(sMessage) && channel.IsDetached()) {
            m_pUser->PutStatusNotice("#" + channel.GetName() + " <" +
                nick.GetNick() + "> " + sMessage);
        }

        return CONTINUE;
    }
};

MODULEDEFS(CDetachedHighlight, "Forwards notices containing any highlights received in detached channels.")
