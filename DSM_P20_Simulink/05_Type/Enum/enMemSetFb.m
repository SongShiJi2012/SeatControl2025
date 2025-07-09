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
            desc = '��������״̬&#10;0���޶���&#10;1��λ��1����ɹ�&#10;2��λ��2����ɹ�&#10;3��λ��3����ɹ�&#10;4��λ�ü���ʧ��&#10;5-7��Ԥ��,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
