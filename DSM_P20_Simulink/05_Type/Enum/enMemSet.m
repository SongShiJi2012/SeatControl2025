%% Create enMemSet enum

classdef enMemSet < Simulink.IntEnumType

    enumeration
        EN_MemSet_NULL(0)
        EN_MemSet_Call(1)
        EN_MemSet_Mem(2)
        EN_MemSet_Clean(3)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enMemSet.EN_MemSet_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '��������&#10;0����&#10;1������λ�� &#10;2�����䵱ǰλ��,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
