function [result] = get_channel(img,channel_id)
[height,width,~] = size(img);
if(channel_id<0||channel_id>3)
    result = zeros(height,width);
else
    for i = 1:3
        if(channel_id == i)
            result(:,:,i)=img(:,:,i);
        else
            result(:,:,i)=zeros(height,width);
        end
    end
    result = uint8(result);
end
end

