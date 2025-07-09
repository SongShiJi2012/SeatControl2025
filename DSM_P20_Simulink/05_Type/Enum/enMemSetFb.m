%% Create enMemSetFb enum

classdef enMemSetFb < Simulink.IntEnumType

    enumeration
        EN_MemSetFb_NULL(0)
        EN_MemSetFb_S1(1)
        EN_MemSetFb_S2(2)
        EN_MemSetFb_S3(3)
        EN_MemSetFb_Fail(4)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enMemSetFb.EN_MemSetFb_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '记忆设置状态&#10;0：无动作&#10;1：位置1记忆成功&#10;2：位置2记忆成功&#10;3：位置3记忆成功&#10;4：位置记忆失败&#10;5-7：预留,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
