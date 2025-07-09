%% Create enResCallRet enum

classdef enResCallRet < Simulink.IntEnumType

    enumeration
        EN_Init(0)
        EN_Fail(1)
        EN_Success(2)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enResCallRet.EN_Init;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '���ε����˶�״̬��&#10;0��Init ��ʼ״̬&#10;1��Fail&#10;2��Success&#10;,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
