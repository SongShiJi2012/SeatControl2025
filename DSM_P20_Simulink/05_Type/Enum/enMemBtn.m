%% Create enMemBtn enum

classdef enMemBtn < Simulink.IntEnumType

    enumeration
        EN_MemBtn_NULL(0)
        EN_MemBtn_Set1(1)
        EN_MemBtn_Call1(2)
        EN_MemBtn_Clear1(3)
        EN_MemBtn_Set2(4)
        EN_MemBtn_Call2(5)
        EN_MemBtn_Clear2(6)
        EN_MemBtn_Set3(7)
        EN_MemBtn_Call3(8)
        EN_MemBtn_Clear3(9)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enMemBtn.EN_MemBtn_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '���䰴ť����&#10;0����&#10;1������1&#10;2������1&#10;3�����1&#10;4������2&#10;5������2&#10;6�����2&#10;7������3&#10;8������3&#10;9�����3,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
