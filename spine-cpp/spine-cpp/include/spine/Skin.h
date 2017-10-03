/******************************************************************************
 * Spine Runtimes Software License v2.5
 *
 * Copyright (c) 2013-2016, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable, and
 * non-transferable license to use, install, execute, and perform the Spine
 * Runtimes software and derivative works solely for personal or internal
 * use. Without the written permission of Esoteric Software (see Section 2 of
 * the Spine Software License Agreement), you may not (a) modify, translate,
 * adapt, or develop new applications using the Spine Runtimes or otherwise
 * create derivative works or improvements of the Spine Runtimes or (b) remove,
 * delete, alter, or obscure any trademarks or any copyright, trademark, patent,
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS INTERRUPTION, OR LOSS OF
 * USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef Spine_Skin_h
#define Spine_Skin_h

#include <string>
#include <vector>
#include <unordered_map>

namespace Spine
{
    class Attachment;
    class Skeleton;
    
    class AttachmentKey;
    
    /// Stores attachments by slot index and attachment name.
    /// See SkeletonData::getDefaultSkin, Skeleton::getSkin, and
    /// http://esotericsoftware.com/spine-runtime-skins in the Spine Runtimes Guide.
    class Skin
    {
    public:
        Skin(std::string name);
        
        /// Adds an attachment to the skin for the specified slot index and name.
        /// If the name already exists for the slot, the previous value is replaced.
        void addAttachment(int slotIndex, std::string name, Attachment* attachment);
        
        /// Returns the attachment for the specified slot index and name, or null.
        Attachment* getAttachment(int slotIndex, std::string name);
        
        /// Finds the skin keys for a given slot. The results are added to the passed vector names.
        /// @param slotIndex The target slotIndex. To find the slot index, use Skeleton::findSlotIndex or SkeletonData::findSlotIndex
        /// @param names Found skin key names will be added to this vector.
        void findNamesForSlot(int slotIndex, std::vector<std::string>& names);
        
        /// Finds the attachments for a given slot. The results are added to the passed List(Attachment).
        /// @param slotIndex The target slotIndex. To find the slot index, use Skeleton::findSlotIndex or SkeletonData::findSlotIndex
        /// @param attachments Found Attachments will be added to this vector.
        void findAttachmentsForSlot(int slotIndex, std::vector<Attachment*>& attachments);
        
        const std::string& getName();
        std::unordered_map<AttachmentKey, Attachment*>& getAttachments();
        
    private:
        const std::string _name;
        std::unordered_map<AttachmentKey, Attachment*> _attachments;
        
        /// Attach all attachments from this skin if the corresponding attachment from the old skin is currently attached.
        void attachAll(Skeleton& skeleton, Skin& oldSkin);
        
        class AttachmentKey
        {
        public:
            const int _slotIndex;
            const std::string _name;
            
            AttachmentKey(int slotIndex, std::string name);
            
            bool operator==(const AttachmentKey &other) const;
        };
        
        friend std::ostream& operator <<(std::ostream& os, const Skin& ref);
        
        namespace std
        {
            template <>
            struct hash<AttachmentKey>
            {
                size_t operator()(const AttachmentKey& val) const
                {
                    size_t h1 = hash<int>{}(val._slotIndex);
                    size_t h2 = hash<string>{}(val._name);
                    
                    return h1 ^ (h2 << 1);
                }
            };
        }
    };
}

#endif /* Spine_Skin_h */
