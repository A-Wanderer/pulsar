/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#pragma once

#include <cstdint>
#include <memory>

namespace pulsar {

class MessageIdImpl;
typedef std::shared_ptr<MessageIdImpl> MessageIdImplPtr;

class ChunkMessageIdImpl: public MessageIdImpl, public std::enable_shared_from_this<ChunkMessageIdImpl> {
   public:
    ChunkMessageIdImpl(MessageIdImpl firstChunkMsgId, MessageIdImpl lastChunkMsgId):
        MessageIdImpl(lastChunkMsgId.ledgerId_, lastChunkMsgId.entryId_, lastChunkMsgId.partition_, lastChunkMsgId.batchIndex_) {
        firstChunkMsgId_ = std::make_shared<MessageIdImpl>(
                           firstChunkMsgId.ledgerId_, firstChunkMsgId.entryId_, firstChunkMsgId.partition_, firstChunkMsgId.batchIndex_);
    }
   
    MessageIdImplPtr getFirstChunkMessageIdImpl() {
        return firstChunkMsgId_;
    }

    MessageIdImplPtr getLastChunkMessageIdImpl() {
        return std::dynamic_pointer_cast<MessageIdImpl>(shared_from_this());
    }

   private:
    MessageIdImplPtr firstChunkMsgId_;
};
}  // namespace pulsar
